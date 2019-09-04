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
struct opal_dev {size_t pos; int /*<<< orphan*/ * cmd; } ;

/* Variables and functions */
 int ERANGE ; 
 size_t IO_BUFFER_LENGTH ; 
 size_t SHORT_ATOM_LEN_MASK ; 
 int /*<<< orphan*/  add_medium_atom_header (struct opal_dev*,int,int,size_t) ; 
 int /*<<< orphan*/  add_short_atom_header (struct opal_dev*,int,int,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void add_token_bytestring(int *err, struct opal_dev *cmd,
				 const u8 *bytestring, size_t len)
{
	size_t header_len = 1;
	bool is_short_atom = true;

	if (*err)
		return;

	if (len & ~SHORT_ATOM_LEN_MASK) {
		header_len = 2;
		is_short_atom = false;
	}

	if (len >= IO_BUFFER_LENGTH - cmd->pos - header_len) {
		pr_debug("Error adding bytestring: end of buffer.\n");
		*err = -ERANGE;
		return;
	}

	if (is_short_atom)
		add_short_atom_header(cmd, true, false, len);
	else
		add_medium_atom_header(cmd, true, false, len);

	memcpy(&cmd->cmd[cmd->pos], bytestring, len);
	cmd->pos += len;

}