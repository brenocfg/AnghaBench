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
typedef  int uint32_t ;
struct radeon_cs_parser {scalar_t__ idx; TYPE_3__* rdev; TYPE_1__* chunk_ib; } ;
struct TYPE_5__ {int* img_size; int /*<<< orphan*/ * handles; } ;
struct TYPE_6__ {TYPE_2__ vce; } ;
struct TYPE_4__ {scalar_t__ length_dw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int ENOENT ; 
 int RADEON_MAX_VCE_HANDLES ; 
 int /*<<< orphan*/  atomic_cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int radeon_get_ib_value (struct radeon_cs_parser*,scalar_t__) ; 
 int radeon_vce_cs_reloc (struct radeon_cs_parser*,scalar_t__,scalar_t__,int) ; 
 int radeon_vce_validate_handle (struct radeon_cs_parser*,int,int*) ; 

int radeon_vce_cs_parse(struct radeon_cs_parser *p)
{
	int session_idx = -1;
	bool destroyed = false, created = false, allocated = false;
	uint32_t tmp, handle = 0;
	uint32_t *size = &tmp;
	int i, r = 0;

	while (p->idx < p->chunk_ib->length_dw) {
		uint32_t len = radeon_get_ib_value(p, p->idx);
		uint32_t cmd = radeon_get_ib_value(p, p->idx + 1);

		if ((len < 8) || (len & 3)) {
			DRM_ERROR("invalid VCE command length (%d)!\n", len);
			r = -EINVAL;
			goto out;
		}

		if (destroyed) {
			DRM_ERROR("No other command allowed after destroy!\n");
			r = -EINVAL;
			goto out;
		}

		switch (cmd) {
		case 0x00000001: // session
			handle = radeon_get_ib_value(p, p->idx + 2);
			session_idx = radeon_vce_validate_handle(p, handle,
								 &allocated);
			if (session_idx < 0)
				return session_idx;
			size = &p->rdev->vce.img_size[session_idx];
			break;

		case 0x00000002: // task info
			break;

		case 0x01000001: // create
			created = true;
			if (!allocated) {
				DRM_ERROR("Handle already in use!\n");
				r = -EINVAL;
				goto out;
			}

			*size = radeon_get_ib_value(p, p->idx + 8) *
				radeon_get_ib_value(p, p->idx + 10) *
				8 * 3 / 2;
			break;

		case 0x04000001: // config extension
		case 0x04000002: // pic control
		case 0x04000005: // rate control
		case 0x04000007: // motion estimation
		case 0x04000008: // rdo
		case 0x04000009: // vui
			break;

		case 0x03000001: // encode
			r = radeon_vce_cs_reloc(p, p->idx + 10, p->idx + 9,
						*size);
			if (r)
				goto out;

			r = radeon_vce_cs_reloc(p, p->idx + 12, p->idx + 11,
						*size / 3);
			if (r)
				goto out;
			break;

		case 0x02000001: // destroy
			destroyed = true;
			break;

		case 0x05000001: // context buffer
			r = radeon_vce_cs_reloc(p, p->idx + 3, p->idx + 2,
						*size * 2);
			if (r)
				goto out;
			break;

		case 0x05000004: // video bitstream buffer
			tmp = radeon_get_ib_value(p, p->idx + 4);
			r = radeon_vce_cs_reloc(p, p->idx + 3, p->idx + 2,
						tmp);
			if (r)
				goto out;
			break;

		case 0x05000005: // feedback buffer
			r = radeon_vce_cs_reloc(p, p->idx + 3, p->idx + 2,
						4096);
			if (r)
				goto out;
			break;

		default:
			DRM_ERROR("invalid VCE command (0x%x)!\n", cmd);
			r = -EINVAL;
			goto out;
		}

		if (session_idx == -1) {
			DRM_ERROR("no session command at start of IB\n");
			r = -EINVAL;
			goto out;
		}

		p->idx += len / 4;
	}

	if (allocated && !created) {
		DRM_ERROR("New session without create command!\n");
		r = -ENOENT;
	}

out:
	if ((!r && destroyed) || (r && allocated)) {
		/*
		 * IB contains a destroy msg or we have allocated an
		 * handle and got an error, anyway free the handle
		 */
		for (i = 0; i < RADEON_MAX_VCE_HANDLES; ++i)
			atomic_cmpxchg(&p->rdev->vce.handles[i], handle, 0);
	}

	return r;
}