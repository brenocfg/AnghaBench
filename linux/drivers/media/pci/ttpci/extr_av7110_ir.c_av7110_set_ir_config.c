#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ir_config; } ;
struct av7110 {TYPE_1__ ir; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMTYPE_PIDFILTER ; 
 int /*<<< orphan*/  SetIR ; 
 int av7110_fw_cmd (struct av7110*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ) ; 

int av7110_set_ir_config(struct av7110 *av7110)
{
	dprintk(4, "ir config = %08x\n", av7110->ir.ir_config);

	return av7110_fw_cmd(av7110, COMTYPE_PIDFILTER, SetIR, 1,
			     av7110->ir.ir_config);
}