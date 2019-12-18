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
struct sja1105_port_status_hl2 {int /*<<< orphan*/  n_not_reach; int /*<<< orphan*/  n_egr_disabled; int /*<<< orphan*/  n_part_drop; int /*<<< orphan*/  n_qfull; } ;

/* Variables and functions */
 int /*<<< orphan*/  sja1105_unpack (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sja1105_port_status_hl2_unpack(void *buf,
			       struct sja1105_port_status_hl2 *status)
{
	/* Make pointer arithmetic work on 4 bytes */
	u32 *p = buf;

	sja1105_unpack(p + 0x3, &status->n_qfull,        31,  0, 4);
	sja1105_unpack(p + 0x2, &status->n_part_drop,    31,  0, 4);
	sja1105_unpack(p + 0x1, &status->n_egr_disabled, 31,  0, 4);
	sja1105_unpack(p + 0x0, &status->n_not_reach,    31,  0, 4);
}