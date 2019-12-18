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
struct wilc {int dummy; } ;
struct sdio_cmd52 {int address; int data; scalar_t__ raw; scalar_t__ function; scalar_t__ read_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  wilc_sdio_cmd52 (struct wilc*,struct sdio_cmd52*) ; 

__attribute__((used)) static int wilc_sdio_read_size(struct wilc *wilc, u32 *size)
{
	u32 tmp;
	struct sdio_cmd52 cmd;

	/**
	 *      Read DMA count in words
	 **/
	cmd.read_write = 0;
	cmd.function = 0;
	cmd.raw = 0;
	cmd.address = 0xf2;
	cmd.data = 0;
	wilc_sdio_cmd52(wilc, &cmd);
	tmp = cmd.data;

	cmd.address = 0xf3;
	cmd.data = 0;
	wilc_sdio_cmd52(wilc, &cmd);
	tmp |= (cmd.data << 8);

	*size = tmp;
	return 1;
}