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
struct gpmi_transfer {int dummy; } ;
struct gpmi_nand_data {size_t ntransfers; struct gpmi_transfer* transfers; } ;

/* Variables and functions */
 size_t GPMI_MAX_TRANSFERS ; 

__attribute__((used)) static struct gpmi_transfer *get_next_transfer(struct gpmi_nand_data *this)
{
	struct gpmi_transfer *transfer = &this->transfers[this->ntransfers];

	this->ntransfers++;

	if (this->ntransfers == GPMI_MAX_TRANSFERS)
		return NULL;

	return transfer;
}