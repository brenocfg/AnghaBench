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
struct scif_port_id {int dummy; } ;
typedef  int /*<<< orphan*/  scif_epd_t ;

/* Variables and functions */
 int __scif_connect (int /*<<< orphan*/ ,struct scif_port_id*,int) ; 

int scif_connect(scif_epd_t epd, struct scif_port_id *dst)
{
	return __scif_connect(epd, dst, false);
}