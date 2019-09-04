#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cryp_device_data {TYPE_1__* base; } ;
typedef  enum cryp_crypen { ____Placeholder_cryp_crypen } cryp_crypen ;
struct TYPE_2__ {int /*<<< orphan*/  cr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYP_CR_CRYPEN_MASK ; 
 int /*<<< orphan*/  CRYP_CR_CRYPEN_POS ; 
 int /*<<< orphan*/  CRYP_PUT_BITS (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cryp_activity(struct cryp_device_data *device_data,
		   enum cryp_crypen cryp_crypen)
{
	CRYP_PUT_BITS(&device_data->base->cr,
		      cryp_crypen,
		      CRYP_CR_CRYPEN_POS,
		      CRYP_CR_CRYPEN_MASK);
}