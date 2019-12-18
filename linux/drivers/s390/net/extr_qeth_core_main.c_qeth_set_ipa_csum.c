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
struct qeth_card {int dummy; } ;
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;

/* Variables and functions */
 int qeth_set_csum_off (struct qeth_card*,int,int) ; 
 int qeth_set_csum_on (struct qeth_card*,int,int) ; 

__attribute__((used)) static int qeth_set_ipa_csum(struct qeth_card *card, bool on, int cstype,
			     enum qeth_prot_versions prot)
{
	return on ? qeth_set_csum_on(card, cstype, prot) :
		    qeth_set_csum_off(card, cstype, prot);
}