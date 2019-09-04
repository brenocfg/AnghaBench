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
typedef  int /*<<< orphan*/  u8 ;
struct opal_resp_tok {int len; int /*<<< orphan*/  width; int /*<<< orphan*/  type; int /*<<< orphan*/  const* pos; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_DTA_TOKENID_TOKEN ; 
 int /*<<< orphan*/  OPAL_WIDTH_TOKEN ; 

__attribute__((used)) static ssize_t response_parse_token(struct opal_resp_tok *tok,
				    const u8 *pos)
{
	tok->pos = pos;
	tok->len = 1;
	tok->type = OPAL_DTA_TOKENID_TOKEN;
	tok->width = OPAL_WIDTH_TOKEN;

	return tok->len;
}