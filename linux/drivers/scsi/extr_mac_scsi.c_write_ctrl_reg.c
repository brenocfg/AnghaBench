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
struct NCR5380_hostdata {scalar_t__ io; } ;

/* Variables and functions */
 int CTRL_REG ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void write_ctrl_reg(struct NCR5380_hostdata *hostdata, u32 value)
{
	out_be32(hostdata->io + (CTRL_REG << 4), value);
}