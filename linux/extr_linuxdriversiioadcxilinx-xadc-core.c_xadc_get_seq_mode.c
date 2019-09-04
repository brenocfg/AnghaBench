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
struct xadc {scalar_t__ external_mux_mode; } ;

/* Variables and functions */
 int XADC_CONF1_SEQ_CONTINUOUS ; 
 int XADC_CONF1_SEQ_SIMULTANEOUS ; 
 scalar_t__ XADC_EXTERNAL_MUX_DUAL ; 

__attribute__((used)) static int xadc_get_seq_mode(struct xadc *xadc, unsigned long scan_mode)
{
	unsigned int aux_scan_mode = scan_mode >> 16;

	if (xadc->external_mux_mode == XADC_EXTERNAL_MUX_DUAL)
		return XADC_CONF1_SEQ_SIMULTANEOUS;

	if ((aux_scan_mode & 0xff00) == 0 ||
		(aux_scan_mode & 0x00ff) == 0)
		return XADC_CONF1_SEQ_CONTINUOUS;

	return XADC_CONF1_SEQ_SIMULTANEOUS;
}