#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct urb {char* transfer_buffer; int transfer_buffer_length; } ;
struct TYPE_5__ {int width; int height; int* pitches; TYPE_1__* format; struct drm_device* dev; } ;
struct udl_framebuffer {TYPE_3__* obj; TYPE_2__ base; int /*<<< orphan*/  active_16; } ;
struct udl_device {int /*<<< orphan*/  cpu_kcycles_used; int /*<<< orphan*/  bytes_rendered; int /*<<< orphan*/  bytes_identical; int /*<<< orphan*/  bytes_sent; } ;
struct drm_device {int dummy; } ;
typedef  int cycles_t ;
struct TYPE_6__ {scalar_t__ vmapping; } ;
struct TYPE_4__ {int /*<<< orphan*/ * cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DL_ALIGN_DOWN (int,int) ; 
 int DL_ALIGN_UP (int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int __ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add (unsigned int,int /*<<< orphan*/ *) ; 
 int get_cycles () ; 
 int /*<<< orphan*/  is_power_of_2 (int /*<<< orphan*/ ) ; 
 struct udl_device* to_udl (struct drm_device*) ; 
 int udl_gem_vmap (TYPE_3__*) ; 
 struct urb* udl_get_urb (struct drm_device*) ; 
 scalar_t__ udl_render_hline (struct drm_device*,int,struct urb**,char*,char**,int const,int const,int,int*,int*) ; 
 int udl_submit_urb (struct drm_device*,struct urb*,int) ; 
 int /*<<< orphan*/  udl_urb_completion (struct urb*) ; 

int udl_handle_damage(struct udl_framebuffer *fb, int x, int y,
		      int width, int height)
{
	struct drm_device *dev = fb->base.dev;
	struct udl_device *udl = to_udl(dev);
	int i, ret;
	char *cmd;
	cycles_t start_cycles, end_cycles;
	int bytes_sent = 0;
	int bytes_identical = 0;
	struct urb *urb;
	int aligned_x;
	int log_bpp;

	BUG_ON(!is_power_of_2(fb->base.format->cpp[0]));
	log_bpp = __ffs(fb->base.format->cpp[0]);

	if (!fb->active_16)
		return 0;

	if (!fb->obj->vmapping) {
		ret = udl_gem_vmap(fb->obj);
		if (ret == -ENOMEM) {
			DRM_ERROR("failed to vmap fb\n");
			return 0;
		}
		if (!fb->obj->vmapping) {
			DRM_ERROR("failed to vmapping\n");
			return 0;
		}
	}

	aligned_x = DL_ALIGN_DOWN(x, sizeof(unsigned long));
	width = DL_ALIGN_UP(width + (x-aligned_x), sizeof(unsigned long));
	x = aligned_x;

	if ((width <= 0) ||
	    (x + width > fb->base.width) ||
	    (y + height > fb->base.height))
		return -EINVAL;

	start_cycles = get_cycles();

	urb = udl_get_urb(dev);
	if (!urb)
		return 0;
	cmd = urb->transfer_buffer;

	for (i = y; i < y + height ; i++) {
		const int line_offset = fb->base.pitches[0] * i;
		const int byte_offset = line_offset + (x << log_bpp);
		const int dev_byte_offset = (fb->base.width * i + x) << log_bpp;
		if (udl_render_hline(dev, log_bpp, &urb,
				     (char *) fb->obj->vmapping,
				     &cmd, byte_offset, dev_byte_offset,
				     width << log_bpp,
				     &bytes_identical, &bytes_sent))
			goto error;
	}

	if (cmd > (char *) urb->transfer_buffer) {
		/* Send partial buffer remaining before exiting */
		int len;
		if (cmd < (char *) urb->transfer_buffer + urb->transfer_buffer_length)
			*cmd++ = 0xAF;
		len = cmd - (char *) urb->transfer_buffer;
		ret = udl_submit_urb(dev, urb, len);
		bytes_sent += len;
	} else
		udl_urb_completion(urb);

error:
	atomic_add(bytes_sent, &udl->bytes_sent);
	atomic_add(bytes_identical, &udl->bytes_identical);
	atomic_add((width * height) << log_bpp, &udl->bytes_rendered);
	end_cycles = get_cycles();
	atomic_add(((unsigned int) ((end_cycles - start_cycles)
		    >> 10)), /* Kcycles */
		   &udl->cpu_kcycles_used);

	return 0;
}