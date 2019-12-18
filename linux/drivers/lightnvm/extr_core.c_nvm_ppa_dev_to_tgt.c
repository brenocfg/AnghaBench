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
struct ppa_addr {int dummy; } ;
struct nvm_tgt_dev {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct ppa_addr dev_to_generic_addr (int /*<<< orphan*/ ,struct ppa_addr) ; 
 int /*<<< orphan*/  nvm_map_to_tgt (struct nvm_tgt_dev*,struct ppa_addr*) ; 

__attribute__((used)) static void nvm_ppa_dev_to_tgt(struct nvm_tgt_dev *tgt_dev,
				struct ppa_addr *ppa_list, int nr_ppas)
{
	int i;

	for (i = 0; i < nr_ppas; i++) {
		ppa_list[i] = dev_to_generic_addr(tgt_dev->parent, ppa_list[i]);
		nvm_map_to_tgt(tgt_dev, &ppa_list[i]);
	}
}