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
struct hwicap_drvdata {scalar_t__ base_address; } ;

/* Variables and functions */
 scalar_t__ XHI_STATUS_REG_OFFSET ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int) ; 

void buffer_icap_reset(struct hwicap_drvdata *drvdata)
{
    out_be32(drvdata->base_address + XHI_STATUS_REG_OFFSET, 0xFEFE);
}