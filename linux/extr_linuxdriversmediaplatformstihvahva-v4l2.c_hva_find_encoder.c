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
typedef  scalar_t__ u32 ;
struct hva_enc {scalar_t__ pixelformat; scalar_t__ streamformat; } ;
struct hva_dev {unsigned int nb_of_encoders; struct hva_enc** encoders; } ;
struct hva_ctx {int dummy; } ;

/* Variables and functions */
 struct hva_dev* ctx_to_hdev (struct hva_ctx*) ; 

__attribute__((used)) static const struct hva_enc *hva_find_encoder(struct hva_ctx *ctx,
					      u32 pixelformat,
					      u32 streamformat)
{
	struct hva_dev *hva = ctx_to_hdev(ctx);
	const struct hva_enc *enc;
	unsigned int i;

	for (i = 0; i < hva->nb_of_encoders; i++) {
		enc = hva->encoders[i];
		if ((enc->pixelformat == pixelformat) &&
		    (enc->streamformat == streamformat))
			return enc;
	}

	return NULL;
}