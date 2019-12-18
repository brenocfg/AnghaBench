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
struct bfi_ioc_attr_s {scalar_t__ port_mode; void* mfg_year; void* maxfrsize; void* card_type; void* adapter_prop; } ;
struct bfa_ioc_s {int fcmode; struct bfi_ioc_attr_s* attr; } ;

/* Variables and functions */
 scalar_t__ BFI_PORT_MODE_FC ; 
 int /*<<< orphan*/  IOC_E_FWRSP_GETATTR ; 
 void* be16_to_cpu (void*) ; 
 void* be32_to_cpu (void*) ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_getattr_reply(struct bfa_ioc_s *ioc)
{
	struct bfi_ioc_attr_s	*attr = ioc->attr;

	attr->adapter_prop  = be32_to_cpu(attr->adapter_prop);
	attr->card_type     = be32_to_cpu(attr->card_type);
	attr->maxfrsize	    = be16_to_cpu(attr->maxfrsize);
	ioc->fcmode	= (attr->port_mode == BFI_PORT_MODE_FC);
	attr->mfg_year	= be16_to_cpu(attr->mfg_year);

	bfa_fsm_send_event(ioc, IOC_E_FWRSP_GETATTR);
}