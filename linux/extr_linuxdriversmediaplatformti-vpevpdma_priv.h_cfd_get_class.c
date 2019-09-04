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
struct vpdma_cfd {int ctl_payload_len; } ;

/* Variables and functions */
 int CFD_CLASS_MASK ; 
 int CFD_CLASS_SHFT ; 

__attribute__((used)) static inline bool cfd_get_class(struct vpdma_cfd *cfd)
{
	return (cfd->ctl_payload_len >> CFD_CLASS_SHFT) & CFD_CLASS_MASK;
}