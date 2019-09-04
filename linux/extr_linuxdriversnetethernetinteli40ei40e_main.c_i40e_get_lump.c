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
typedef  int u16 ;
struct i40e_pf {TYPE_1__* pdev; } ;
struct i40e_lump_tracking {int search_hint; int num_entries; int* list; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int I40E_PILE_VALID_BIT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,int,int) ; 

__attribute__((used)) static int i40e_get_lump(struct i40e_pf *pf, struct i40e_lump_tracking *pile,
			 u16 needed, u16 id)
{
	int ret = -ENOMEM;
	int i, j;

	if (!pile || needed == 0 || id >= I40E_PILE_VALID_BIT) {
		dev_info(&pf->pdev->dev,
			 "param err: pile=%s needed=%d id=0x%04x\n",
			 pile ? "<valid>" : "<null>", needed, id);
		return -EINVAL;
	}

	/* start the linear search with an imperfect hint */
	i = pile->search_hint;
	while (i < pile->num_entries) {
		/* skip already allocated entries */
		if (pile->list[i] & I40E_PILE_VALID_BIT) {
			i++;
			continue;
		}

		/* do we have enough in this lump? */
		for (j = 0; (j < needed) && ((i+j) < pile->num_entries); j++) {
			if (pile->list[i+j] & I40E_PILE_VALID_BIT)
				break;
		}

		if (j == needed) {
			/* there was enough, so assign it to the requestor */
			for (j = 0; j < needed; j++)
				pile->list[i+j] = id | I40E_PILE_VALID_BIT;
			ret = i;
			pile->search_hint = i + j;
			break;
		}

		/* not enough, so skip over it and continue looking */
		i += j;
	}

	return ret;
}