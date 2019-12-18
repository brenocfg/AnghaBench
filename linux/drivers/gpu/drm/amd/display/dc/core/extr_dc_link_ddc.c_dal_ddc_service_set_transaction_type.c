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
struct ddc_service {int transaction_type; } ;
typedef  enum ddc_transaction_type { ____Placeholder_ddc_transaction_type } ddc_transaction_type ;

/* Variables and functions */

void dal_ddc_service_set_transaction_type(
	struct ddc_service *ddc,
	enum ddc_transaction_type type)
{
	ddc->transaction_type = type;
}