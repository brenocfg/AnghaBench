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
struct gsm_dlci {int /*<<< orphan*/  gsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  gsm_control_message (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  gsm_control_response (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/  const*,int) ; 
 int gsm_read_ea (unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gsm_dlci_command(struct gsm_dlci *dlci, const u8 *data, int len)
{
	/* See what command is involved */
	unsigned int command = 0;
	while (len-- > 0) {
		if (gsm_read_ea(&command, *data++) == 1) {
			int clen = *data++;
			len--;
			/* FIXME: this is properly an EA */
			clen >>= 1;
			/* Malformed command ? */
			if (clen > len)
				return;
			if (command & 1)
				gsm_control_message(dlci->gsm, command,
								data, clen);
			else
				gsm_control_response(dlci->gsm, command,
								data, clen);
			return;
		}
	}
}