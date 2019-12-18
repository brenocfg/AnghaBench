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
struct ucsi_connector {int /*<<< orphan*/ * partner; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCSI_RECIPIENT_SOP ; 
 int /*<<< orphan*/  typec_unregister_partner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucsi_unregister_altmodes (struct ucsi_connector*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ucsi_unregister_partner(struct ucsi_connector *con)
{
	if (!con->partner)
		return;

	ucsi_unregister_altmodes(con, UCSI_RECIPIENT_SOP);
	typec_unregister_partner(con->partner);
	con->partner = NULL;
}