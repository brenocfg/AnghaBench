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
struct sja1105_port_status_hl2 {int /*<<< orphan*/ * qlevel; int /*<<< orphan*/ * qlevel_hwm; } ;

/* Variables and functions */
 int /*<<< orphan*/  sja1105_unpack (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void
sja1105pqrs_port_status_qlevel_unpack(void *buf,
				      struct sja1105_port_status_hl2 *status)
{
	/* Make pointer arithmetic work on 4 bytes */
	u32 *p = buf;
	int i;

	for (i = 0; i < 8; i++) {
		sja1105_unpack(p + i, &status->qlevel_hwm[i], 24, 16, 4);
		sja1105_unpack(p + i, &status->qlevel[i],      8,  0, 4);
	}
}