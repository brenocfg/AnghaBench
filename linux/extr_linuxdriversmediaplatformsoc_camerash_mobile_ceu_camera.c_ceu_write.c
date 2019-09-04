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
struct sh_mobile_ceu_dev {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ceu_write(struct sh_mobile_ceu_dev *priv,
		      unsigned long reg_offs, u32 data)
{
	iowrite32(data, priv->base + reg_offs);
}