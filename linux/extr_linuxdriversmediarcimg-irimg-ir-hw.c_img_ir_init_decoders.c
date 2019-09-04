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
struct img_ir_decoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  img_ir_decoder_preprocess (struct img_ir_decoder*) ; 
 struct img_ir_decoder** img_ir_decoders ; 
 int /*<<< orphan*/  img_ir_decoders_lock ; 
 int img_ir_decoders_preprocessed ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void img_ir_init_decoders(void)
{
	struct img_ir_decoder **decp;

	spin_lock(&img_ir_decoders_lock);
	if (!img_ir_decoders_preprocessed) {
		for (decp = img_ir_decoders; *decp; ++decp)
			img_ir_decoder_preprocess(*decp);
		img_ir_decoders_preprocessed = true;
	}
	spin_unlock(&img_ir_decoders_lock);
}