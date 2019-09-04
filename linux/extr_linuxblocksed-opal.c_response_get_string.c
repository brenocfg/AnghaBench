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
typedef  int u8 ;
struct parsed_resp {int num; struct opal_resp_tok* toks; } ;
struct opal_resp_tok {scalar_t__ type; int width; char* pos; size_t len; } ;

/* Variables and functions */
 scalar_t__ OPAL_DTA_TOKENID_BYTESTRING ; 
#define  OPAL_WIDTH_LONG 131 
#define  OPAL_WIDTH_MEDIUM 130 
#define  OPAL_WIDTH_SHORT 129 
#define  OPAL_WIDTH_TINY 128 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static size_t response_get_string(const struct parsed_resp *resp, int n,
				  const char **store)
{
	u8 skip;
	const struct opal_resp_tok *token;

	*store = NULL;
	if (!resp) {
		pr_debug("Response is NULL\n");
		return 0;
	}

	if (n >= resp->num) {
		pr_debug("Response has %d tokens. Can't access %d\n",
			 resp->num, n);
		return 0;
	}

	token = &resp->toks[n];
	if (token->type != OPAL_DTA_TOKENID_BYTESTRING) {
		pr_debug("Token is not a byte string!\n");
		return 0;
	}

	switch (token->width) {
	case OPAL_WIDTH_TINY:
	case OPAL_WIDTH_SHORT:
		skip = 1;
		break;
	case OPAL_WIDTH_MEDIUM:
		skip = 2;
		break;
	case OPAL_WIDTH_LONG:
		skip = 4;
		break;
	default:
		pr_debug("Token has invalid width!\n");
		return 0;
	}

	*store = token->pos + skip;
	return token->len - skip;
}