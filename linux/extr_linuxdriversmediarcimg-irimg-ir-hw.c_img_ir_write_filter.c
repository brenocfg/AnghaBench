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
typedef  int /*<<< orphan*/  u32 ;
struct img_ir_priv {int /*<<< orphan*/  dev; } ;
struct img_ir_filter {int data; int mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_IR_IRQ_MSG_DATA_LW ; 
 int /*<<< orphan*/  IMG_IR_IRQ_MSG_DATA_UP ; 
 int /*<<< orphan*/  IMG_IR_IRQ_MSG_MASK_LW ; 
 int /*<<< orphan*/  IMG_IR_IRQ_MSG_MASK_UP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  img_ir_write (struct img_ir_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void img_ir_write_filter(struct img_ir_priv *priv,
				struct img_ir_filter *filter)
{
	if (filter) {
		dev_dbg(priv->dev, "IR filter=%016llx & %016llx\n",
			(unsigned long long)filter->data,
			(unsigned long long)filter->mask);
		img_ir_write(priv, IMG_IR_IRQ_MSG_DATA_LW, (u32)filter->data);
		img_ir_write(priv, IMG_IR_IRQ_MSG_DATA_UP, (u32)(filter->data
									>> 32));
		img_ir_write(priv, IMG_IR_IRQ_MSG_MASK_LW, (u32)filter->mask);
		img_ir_write(priv, IMG_IR_IRQ_MSG_MASK_UP, (u32)(filter->mask
									>> 32));
	} else {
		dev_dbg(priv->dev, "IR clearing filter\n");
		img_ir_write(priv, IMG_IR_IRQ_MSG_MASK_LW, 0);
		img_ir_write(priv, IMG_IR_IRQ_MSG_MASK_UP, 0);
	}
}