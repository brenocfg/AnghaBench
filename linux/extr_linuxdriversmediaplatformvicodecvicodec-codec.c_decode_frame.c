#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct raw_frame {int /*<<< orphan*/  cr; int /*<<< orphan*/  cb; int /*<<< orphan*/  luma; } ;
struct cframe {int height; int width; int /*<<< orphan*/ * rlc_data; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int VICODEC_FL_CB_IS_UNCOMPRESSED ; 
 int VICODEC_FL_CR_IS_UNCOMPRESSED ; 
 int VICODEC_FL_LUMA_IS_UNCOMPRESSED ; 
 int /*<<< orphan*/  decode_plane (struct cframe*,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int,int,int) ; 

void decode_frame(struct cframe *cf, struct raw_frame *ref, u32 hdr_flags)
{
	const __be16 *rlco = cf->rlc_data;

	decode_plane(cf, &rlco, ref->luma, cf->height, cf->width,
		     hdr_flags & VICODEC_FL_LUMA_IS_UNCOMPRESSED);
	decode_plane(cf, &rlco, ref->cb, cf->height / 2, cf->width / 2,
		     hdr_flags & VICODEC_FL_CB_IS_UNCOMPRESSED);
	decode_plane(cf, &rlco, ref->cr, cf->height / 2, cf->width / 2,
		     hdr_flags & VICODEC_FL_CR_IS_UNCOMPRESSED);
}