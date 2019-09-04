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
typedef  int u8 ;
struct TYPE_2__ {int u; } ;
struct opal_resp_tok {int const* pos; int len; TYPE_1__ stored; int /*<<< orphan*/  type; int /*<<< orphan*/  width; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_DTA_TOKENID_SINT ; 
 int /*<<< orphan*/  OPAL_DTA_TOKENID_UINT ; 
 int /*<<< orphan*/  OPAL_WIDTH_TINY ; 
 int const TINY_ATOM_SIGNED ; 

__attribute__((used)) static ssize_t response_parse_tiny(struct opal_resp_tok *tok,
				   const u8 *pos)
{
	tok->pos = pos;
	tok->len = 1;
	tok->width = OPAL_WIDTH_TINY;

	if (pos[0] & TINY_ATOM_SIGNED) {
		tok->type = OPAL_DTA_TOKENID_SINT;
	} else {
		tok->type = OPAL_DTA_TOKENID_UINT;
		tok->stored.u = pos[0] & 0x3f;
	}

	return tok->len;
}