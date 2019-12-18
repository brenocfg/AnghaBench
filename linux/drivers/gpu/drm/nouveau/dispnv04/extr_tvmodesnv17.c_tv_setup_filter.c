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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int hdisplay; int vdisplay; } ;
struct nv17_tv_norm_params {TYPE_3__ tv_enc_mode; } ;
struct TYPE_5__ {int* hfilter; int* vfilter; } ;
struct nv17_tv_encoder {int flicker; int /*<<< orphan*/  overscan; TYPE_2__ state; } ;
struct filter_params {int k1; int ki; int ki2; int ki3; int kr; int kir; int ki2r; int ki3r; int kf; int kif; int ki2f; int ki3f; int krf; int kirf; int ki2rf; int ki3rf; } ;
struct drm_encoder {TYPE_1__* crtc; } ;
struct drm_display_mode {int hdisplay; int vdisplay; } ;
typedef  int int64_t ;
typedef  int int32_t ;
struct TYPE_4__ {struct drm_display_mode mode; } ;

/* Variables and functions */
 int calc_overscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 struct filter_params** fparams ; 
 struct nv17_tv_norm_params* get_tv_norm (struct drm_encoder*) ; 
 int /*<<< orphan*/  id2 ; 
 int id3 ; 
 int id5 ; 
 int max (int,int /*<<< orphan*/ ) ; 
 struct nv17_tv_encoder* to_tv_enc (struct drm_encoder*) ; 

__attribute__((used)) static void tv_setup_filter(struct drm_encoder *encoder)
{
	struct nv17_tv_encoder *tv_enc = to_tv_enc(encoder);
	struct nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);
	struct drm_display_mode *mode = &encoder->crtc->mode;
	uint32_t (*filters[])[4][7] = {&tv_enc->state.hfilter,
				       &tv_enc->state.vfilter};
	int i, j, k;
	int32_t overscan = calc_overscan(tv_enc->overscan);
	int64_t flicker = (tv_enc->flicker - 50) * (id3 / 100);
	uint64_t rs[] = {mode->hdisplay * id3,
			 mode->vdisplay * id3};

	do_div(rs[0], overscan * tv_norm->tv_enc_mode.hdisplay);
	do_div(rs[1], overscan * tv_norm->tv_enc_mode.vdisplay);

	for (k = 0; k < 2; k++) {
		rs[k] = max((int64_t)rs[k], id2);

		for (j = 0; j < 4; j++) {
			struct filter_params *p = &fparams[k][j];

			for (i = 0; i < 7; i++) {
				int64_t c = (p->k1 + p->ki*i + p->ki2*i*i +
					     p->ki3*i*i*i)
					+ (p->kr + p->kir*i + p->ki2r*i*i +
					   p->ki3r*i*i*i) * rs[k]
					+ (p->kf + p->kif*i + p->ki2f*i*i +
					   p->ki3f*i*i*i) * flicker
					+ (p->krf + p->kirf*i + p->ki2rf*i*i +
					   p->ki3rf*i*i*i) * flicker * rs[k];

				(*filters[k])[j][i] = (c + id5/2) >> 39
					& (0x1 << 31 | 0x7f << 9);
			}
		}
	}
}