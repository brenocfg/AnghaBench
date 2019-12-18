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
struct cosa_data {int dummy; } ;

/* Variables and functions */
 int COSA_MAX_ID_STRING ; 
 int /*<<< orphan*/  SR_RST ; 
 int /*<<< orphan*/  cosa_getdata8 (struct cosa_data*) ; 
 int /*<<< orphan*/  cosa_putstatus (struct cosa_data*,int /*<<< orphan*/ ) ; 
 int get_wait_data (struct cosa_data*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int cosa_reset_and_read_id(struct cosa_data *cosa, char *idstring)
{
	int i=0, id=0, prev=0, curr=0;

	/* Reset the card ... */
	cosa_putstatus(cosa, 0);
	cosa_getdata8(cosa);
	cosa_putstatus(cosa, SR_RST);
	msleep(500);
	/* Disable all IRQs from the card */
	cosa_putstatus(cosa, 0);

	/*
	 * Try to read the ID string. The card then prints out the
	 * identification string ended by the "\n\x2e".
	 *
	 * The following loop is indexed through i (instead of id)
	 * to avoid looping forever when for any reason
	 * the port returns '\r', '\n' or '\x2e' permanently.
	 */
	for (i=0; i<COSA_MAX_ID_STRING-1; i++, prev=curr) {
		if ((curr = get_wait_data(cosa)) == -1) {
			return -1;
		}
		curr &= 0xff;
		if (curr != '\r' && curr != '\n' && curr != 0x2e)
			idstring[id++] = curr;
		if (curr == 0x2e && prev == '\n')
			break;
	}
	/* Perhaps we should fail when i==COSA_MAX_ID_STRING-1 ? */
	idstring[id] = '\0';
	return id;
}