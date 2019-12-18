#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int dummy; } ;
struct TYPE_6__ {TYPE_1__* adapter; } ;
struct TYPE_5__ {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 TYPE_2__* ICOM_PORT ; 
 int /*<<< orphan*/  icom_kref_release ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int startup (TYPE_2__*) ; 
 int /*<<< orphan*/  trace (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int icom_open(struct uart_port *port)
{
	int retval;

	kref_get(&ICOM_PORT->adapter->kref);
	retval = startup(ICOM_PORT);

	if (retval) {
		kref_put(&ICOM_PORT->adapter->kref, icom_kref_release);
		trace(ICOM_PORT, "STARTUP_ERROR", 0);
		return retval;
	}

	return 0;
}