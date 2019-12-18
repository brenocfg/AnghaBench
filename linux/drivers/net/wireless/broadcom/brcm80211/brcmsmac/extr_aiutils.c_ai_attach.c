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
struct si_pub {int dummy; } ;
struct si_info {int dummy; } ;
struct bcma_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/ * ai_doattach (struct si_info*,struct bcma_bus*) ; 
 int /*<<< orphan*/  kfree (struct si_info*) ; 
 struct si_info* kzalloc (int,int /*<<< orphan*/ ) ; 

struct si_pub *
ai_attach(struct bcma_bus *pbus)
{
	struct si_info *sii;

	/* alloc struct si_info */
	sii = kzalloc(sizeof(struct si_info), GFP_ATOMIC);
	if (sii == NULL)
		return NULL;

	if (ai_doattach(sii, pbus) == NULL) {
		kfree(sii);
		return NULL;
	}

	return (struct si_pub *) sii;
}