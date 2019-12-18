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
typedef  int u8 ;
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sii8620_mt_read_devcap_reg (struct sii8620*,int) ; 

__attribute__((used)) static inline void sii8620_mt_read_xdevcap_reg(struct sii8620 *ctx, u8 reg)
{
	sii8620_mt_read_devcap_reg(ctx, reg | 0x80);
}