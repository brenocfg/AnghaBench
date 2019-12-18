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
typedef  int /*<<< orphan*/  u8 ;
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MHL_SET_INT ; 
 int /*<<< orphan*/  sii8620_mt_msc_cmd (struct sii8620*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sii8620_mt_set_int(struct sii8620 *ctx, u8 irq, u8 mask)
{
	sii8620_mt_msc_cmd(ctx, MHL_SET_INT, irq, mask);
}