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
struct tmc_drvdata {char* buf; scalar_t__ len; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TMC_RRD ; 
 scalar_t__ TMC_STS ; 
 int TMC_STS_FULL ; 
 int /*<<< orphan*/  coresight_insert_barrier_packet (char*) ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void tmc_etb_dump_hw(struct tmc_drvdata *drvdata)
{
	char *bufp;
	u32 read_data, lost;

	/* Check if the buffer wrapped around. */
	lost = readl_relaxed(drvdata->base + TMC_STS) & TMC_STS_FULL;
	bufp = drvdata->buf;
	drvdata->len = 0;
	while (1) {
		read_data = readl_relaxed(drvdata->base + TMC_RRD);
		if (read_data == 0xFFFFFFFF)
			break;
		memcpy(bufp, &read_data, 4);
		bufp += 4;
		drvdata->len += 4;
	}

	if (lost)
		coresight_insert_barrier_packet(drvdata->buf);
	return;
}