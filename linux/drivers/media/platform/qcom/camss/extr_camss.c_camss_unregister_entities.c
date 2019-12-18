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
struct camss {unsigned int csiphy_num; unsigned int csid_num; unsigned int vfe_num; int /*<<< orphan*/ * vfe; int /*<<< orphan*/  ispif; int /*<<< orphan*/ * csid; int /*<<< orphan*/ * csiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msm_csid_unregister_entity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_csiphy_unregister_entity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_ispif_unregister_entities (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_vfe_unregister_entities (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void camss_unregister_entities(struct camss *camss)
{
	unsigned int i;

	for (i = 0; i < camss->csiphy_num; i++)
		msm_csiphy_unregister_entity(&camss->csiphy[i]);

	for (i = 0; i < camss->csid_num; i++)
		msm_csid_unregister_entity(&camss->csid[i]);

	msm_ispif_unregister_entities(&camss->ispif);

	for (i = 0; i < camss->vfe_num; i++)
		msm_vfe_unregister_entities(&camss->vfe[i]);
}