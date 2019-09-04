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
struct cec_pin {TYPE_1__* ops; } ;
struct cec_adapter {struct cec_pin* pin; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (struct cec_adapter*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct cec_pin*) ; 
 int /*<<< orphan*/  stub1 (struct cec_adapter*) ; 

__attribute__((used)) static void cec_pin_adap_free(struct cec_adapter *adap)
{
	struct cec_pin *pin = adap->pin;

	if (pin->ops->free)
		pin->ops->free(adap);
	adap->pin = NULL;
	kfree(pin);
}