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
struct bfi_ioc_attr {int card_type; } ;
struct bfa_ioc {struct bfi_ioc_attr* attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_ADAPTER_MODEL_NAME_LEN ; 
 char* BFA_MFG_NAME ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static void
bfa_ioc_get_adapter_model(struct bfa_ioc *ioc, char *model)
{
	struct bfi_ioc_attr *ioc_attr;

	BUG_ON(!(model));
	memset(model, 0, BFA_ADAPTER_MODEL_NAME_LEN);

	ioc_attr = ioc->attr;

	snprintf(model, BFA_ADAPTER_MODEL_NAME_LEN, "%s-%u",
		BFA_MFG_NAME, ioc_attr->card_type);
}