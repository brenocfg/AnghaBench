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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int BIT_MDT_RCV_CTRL_MDT_DELAY_RCV_EN ; 
 int BIT_MDT_RCV_CTRL_MDT_RCV_EN ; 
 int BIT_MDT_RCV_CTRL_MDT_RFIFO_CLR_CUR ; 
 int /*<<< orphan*/  REG_MDT_RCV_CTRL ; 
 int /*<<< orphan*/  REG_MDT_RCV_READ_PORT ; 
 int /*<<< orphan*/  REG_MDT_RFIFO_STAT ; 
 int /*<<< orphan*/  sii8620_read_buf (struct sii8620*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_readb (struct sii8620*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_write (struct sii8620*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sii8620_read_burst(struct sii8620 *ctx)
{
	u8 buf[17];

	sii8620_read_buf(ctx, REG_MDT_RCV_READ_PORT, buf, ARRAY_SIZE(buf));
	sii8620_write(ctx, REG_MDT_RCV_CTRL, BIT_MDT_RCV_CTRL_MDT_RCV_EN |
		      BIT_MDT_RCV_CTRL_MDT_DELAY_RCV_EN |
		      BIT_MDT_RCV_CTRL_MDT_RFIFO_CLR_CUR);
	sii8620_readb(ctx, REG_MDT_RFIFO_STAT);
}