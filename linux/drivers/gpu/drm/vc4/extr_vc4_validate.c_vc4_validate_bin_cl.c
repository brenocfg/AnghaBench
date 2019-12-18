#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  size_t u8 ;
struct vc4_exec_info {scalar_t__ ct0ca; int /*<<< orphan*/  found_flush; int /*<<< orphan*/  found_increment_semaphore_packet; int /*<<< orphan*/  found_start_tile_binning_packet; scalar_t__ ct0ea; TYPE_1__* args; } ;
struct drm_device {int dummy; } ;
struct cmd_info {scalar_t__ len; int /*<<< orphan*/  name; scalar_t__ (* func ) (struct vc4_exec_info*,void*,void*) ;} ;
struct TYPE_2__ {scalar_t__ bin_cl_size; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct cmd_info*) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int EINVAL ; 
 size_t VC4_PACKET_GEM_HANDLES ; 
 size_t VC4_PACKET_HALT ; 
 struct cmd_info* cmd_info ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 
 scalar_t__ stub1 (struct vc4_exec_info*,void*,void*) ; 

int
vc4_validate_bin_cl(struct drm_device *dev,
		    void *validated,
		    void *unvalidated,
		    struct vc4_exec_info *exec)
{
	uint32_t len = exec->args->bin_cl_size;
	uint32_t dst_offset = 0;
	uint32_t src_offset = 0;

	while (src_offset < len) {
		void *dst_pkt = validated + dst_offset;
		void *src_pkt = unvalidated + src_offset;
		u8 cmd = *(uint8_t *)src_pkt;
		const struct cmd_info *info;

		if (cmd >= ARRAY_SIZE(cmd_info)) {
			DRM_DEBUG("0x%08x: packet %d out of bounds\n",
				  src_offset, cmd);
			return -EINVAL;
		}

		info = &cmd_info[cmd];
		if (!info->name) {
			DRM_DEBUG("0x%08x: packet %d invalid\n",
				  src_offset, cmd);
			return -EINVAL;
		}

		if (src_offset + info->len > len) {
			DRM_DEBUG("0x%08x: packet %d (%s) length 0x%08x "
				  "exceeds bounds (0x%08x)\n",
				  src_offset, cmd, info->name, info->len,
				  src_offset + len);
			return -EINVAL;
		}

		if (cmd != VC4_PACKET_GEM_HANDLES)
			memcpy(dst_pkt, src_pkt, info->len);

		if (info->func && info->func(exec,
					     dst_pkt + 1,
					     src_pkt + 1)) {
			DRM_DEBUG("0x%08x: packet %d (%s) failed to validate\n",
				  src_offset, cmd, info->name);
			return -EINVAL;
		}

		src_offset += info->len;
		/* GEM handle loading doesn't produce HW packets. */
		if (cmd != VC4_PACKET_GEM_HANDLES)
			dst_offset += info->len;

		/* When the CL hits halt, it'll stop reading anything else. */
		if (cmd == VC4_PACKET_HALT)
			break;
	}

	exec->ct0ea = exec->ct0ca + dst_offset;

	if (!exec->found_start_tile_binning_packet) {
		DRM_DEBUG("Bin CL missing VC4_PACKET_START_TILE_BINNING\n");
		return -EINVAL;
	}

	/* The bin CL must be ended with INCREMENT_SEMAPHORE and FLUSH.  The
	 * semaphore is used to trigger the render CL to start up, and the
	 * FLUSH is what caps the bin lists with
	 * VC4_PACKET_RETURN_FROM_SUB_LIST (so they jump back to the main
	 * render CL when they get called to) and actually triggers the queued
	 * semaphore increment.
	 */
	if (!exec->found_increment_semaphore_packet || !exec->found_flush) {
		DRM_DEBUG("Bin CL missing VC4_PACKET_INCREMENT_SEMAPHORE + "
			  "VC4_PACKET_FLUSH\n");
		return -EINVAL;
	}

	return 0;
}