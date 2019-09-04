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
struct ddc_service {int dummy; } ;
typedef  enum ddc_service_type { ____Placeholder_ddc_service_type } ddc_service_type ;

/* Variables and functions */
 int DDC_SERVICE_TYPE_CONNECTOR ; 

enum ddc_service_type dal_ddc_service_get_type(struct ddc_service *ddc)
{
	return DDC_SERVICE_TYPE_CONNECTOR;
}