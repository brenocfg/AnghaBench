#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct parsed_resp {int num; TYPE_2__* toks; } ;
struct TYPE_3__ {int /*<<< orphan*/  u; } ;
struct TYPE_4__ {TYPE_1__ stored; int /*<<< orphan*/  width; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_DTA_TOKENID_UINT ; 
 int /*<<< orphan*/  OPAL_WIDTH_SHORT ; 
 int /*<<< orphan*/  OPAL_WIDTH_TINY ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static u64 response_get_u64(const struct parsed_resp *resp, int n)
{
	if (!resp) {
		pr_debug("Response is NULL\n");
		return 0;
	}

	if (n >= resp->num) {
		pr_debug("Response has %d tokens. Can't access %d\n",
			 resp->num, n);
		return 0;
	}

	if (resp->toks[n].type != OPAL_DTA_TOKENID_UINT) {
		pr_debug("Token is not unsigned it: %d\n",
			 resp->toks[n].type);
		return 0;
	}

	if (!(resp->toks[n].width == OPAL_WIDTH_TINY ||
	      resp->toks[n].width == OPAL_WIDTH_SHORT)) {
		pr_debug("Atom is not short or tiny: %d\n",
			 resp->toks[n].width);
		return 0;
	}

	return resp->toks[n].stored.u;
}