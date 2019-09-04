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
struct fw_initialize_cmd {int dummy; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  INITIALIZE ; 
 int /*<<< orphan*/  INIT_CMD (struct fw_initialize_cmd,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  memset (struct fw_initialize_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,unsigned int,struct fw_initialize_cmd*,int,int /*<<< orphan*/ *) ; 

int t4_early_init(struct adapter *adap, unsigned int mbox)
{
	struct fw_initialize_cmd c;

	memset(&c, 0, sizeof(c));
	INIT_CMD(c, INITIALIZE, WRITE);
	return t4_wr_mbox(adap, mbox, &c, sizeof(c), NULL);
}