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

/* Variables and functions */
 int IB_PROT_T10DIF_TYPE_1 ; 
 int IB_PROT_T10DIF_TYPE_2 ; 
 int IB_PROT_T10DIF_TYPE_3 ; 
 unsigned int SHOST_DIF_TYPE1_PROTECTION ; 
 unsigned int SHOST_DIF_TYPE2_PROTECTION ; 
 unsigned int SHOST_DIF_TYPE3_PROTECTION ; 
 unsigned int SHOST_DIX_TYPE0_PROTECTION ; 
 unsigned int SHOST_DIX_TYPE1_PROTECTION ; 
 unsigned int SHOST_DIX_TYPE2_PROTECTION ; 
 unsigned int SHOST_DIX_TYPE3_PROTECTION ; 

__attribute__((used)) static inline unsigned int
iser_dif_prot_caps(int prot_caps)
{
	return ((prot_caps & IB_PROT_T10DIF_TYPE_1) ?
		SHOST_DIF_TYPE1_PROTECTION | SHOST_DIX_TYPE0_PROTECTION |
		SHOST_DIX_TYPE1_PROTECTION : 0) |
	       ((prot_caps & IB_PROT_T10DIF_TYPE_2) ?
		SHOST_DIF_TYPE2_PROTECTION | SHOST_DIX_TYPE2_PROTECTION : 0) |
	       ((prot_caps & IB_PROT_T10DIF_TYPE_3) ?
		SHOST_DIF_TYPE3_PROTECTION | SHOST_DIX_TYPE3_PROTECTION : 0);
}