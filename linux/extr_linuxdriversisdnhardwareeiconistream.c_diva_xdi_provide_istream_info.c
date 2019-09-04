#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ provided_service; } ;
typedef  TYPE_1__ diva_xdi_stream_interface_t ;
typedef  int /*<<< orphan*/  ADAPTER ;

/* Variables and functions */

void diva_xdi_provide_istream_info(ADAPTER *a,
				   diva_xdi_stream_interface_t *pi) {
	pi->provided_service = 0;
}