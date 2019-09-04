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
struct fore200e {int /*<<< orphan*/  state; TYPE_1__* bus; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* configure ) (struct fore200e*) ;scalar_t__ (* map ) (struct fore200e*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FORE200E_STATE_COMPLETE ; 
 scalar_t__ fore200e_alloc_rx_buf (struct fore200e*) ; 
 scalar_t__ fore200e_get_esi (struct fore200e*) ; 
 scalar_t__ fore200e_init_bs_queue (struct fore200e*) ; 
 scalar_t__ fore200e_init_cmd_queue (struct fore200e*) ; 
 scalar_t__ fore200e_init_rx_queue (struct fore200e*) ; 
 scalar_t__ fore200e_init_tx_queue (struct fore200e*) ; 
 scalar_t__ fore200e_initialize (struct fore200e*) ; 
 scalar_t__ fore200e_irq_request (struct fore200e*) ; 
 scalar_t__ fore200e_load_and_start_fw (struct fore200e*) ; 
 scalar_t__ fore200e_register (struct fore200e*,struct device*) ; 
 scalar_t__ fore200e_reset (struct fore200e*,int) ; 
 int /*<<< orphan*/  fore200e_supply (struct fore200e*) ; 
 scalar_t__ stub1 (struct fore200e*) ; 
 scalar_t__ stub2 (struct fore200e*) ; 

__attribute__((used)) static int fore200e_init(struct fore200e *fore200e, struct device *parent)
{
    if (fore200e_register(fore200e, parent) < 0)
	return -ENODEV;
    
    if (fore200e->bus->configure(fore200e) < 0)
	return -ENODEV;

    if (fore200e->bus->map(fore200e) < 0)
	return -ENODEV;

    if (fore200e_reset(fore200e, 1) < 0)
	return -ENODEV;

    if (fore200e_load_and_start_fw(fore200e) < 0)
	return -ENODEV;

    if (fore200e_initialize(fore200e) < 0)
	return -ENODEV;

    if (fore200e_init_cmd_queue(fore200e) < 0)
	return -ENOMEM;

    if (fore200e_init_tx_queue(fore200e) < 0)
	return -ENOMEM;

    if (fore200e_init_rx_queue(fore200e) < 0)
	return -ENOMEM;

    if (fore200e_init_bs_queue(fore200e) < 0)
	return -ENOMEM;

    if (fore200e_alloc_rx_buf(fore200e) < 0)
	return -ENOMEM;

    if (fore200e_get_esi(fore200e) < 0)
	return -EIO;

    if (fore200e_irq_request(fore200e) < 0)
	return -EBUSY;

    fore200e_supply(fore200e);

    /* all done, board initialization is now complete */
    fore200e->state = FORE200E_STATE_COMPLETE;
    return 0;
}