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
struct ddc_service_init_data {int dummy; } ;
struct ddc_service {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  construct (struct ddc_service*,struct ddc_service_init_data*) ; 
 struct ddc_service* kzalloc (int,int /*<<< orphan*/ ) ; 

struct ddc_service *dal_ddc_service_create(
	struct ddc_service_init_data *init_data)
{
	struct ddc_service *ddc_service;

	ddc_service = kzalloc(sizeof(struct ddc_service), GFP_KERNEL);

	if (!ddc_service)
		return NULL;

	construct(ddc_service, init_data);
	return ddc_service;
}