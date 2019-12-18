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
struct fcoe_transport {int attached; int /*<<< orphan*/  name; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  FCOE_TRANSPORT_DEFAULT ; 
 int /*<<< orphan*/  LIBFCOE_TRANSPORT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcoe_transports ; 
 int /*<<< orphan*/  ft_mutex ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fcoe_transport_attach(struct fcoe_transport *ft)
{
	int rc = 0;

	mutex_lock(&ft_mutex);
	if (ft->attached) {
		LIBFCOE_TRANSPORT_DBG("transport %s already attached\n",
				       ft->name);
		rc = -EEXIST;
		goto out_attach;
	}

	/* Add default transport to the tail */
	if (strcmp(ft->name, FCOE_TRANSPORT_DEFAULT))
		list_add(&ft->list, &fcoe_transports);
	else
		list_add_tail(&ft->list, &fcoe_transports);

	ft->attached = true;
	LIBFCOE_TRANSPORT_DBG("attaching transport %s\n", ft->name);

out_attach:
	mutex_unlock(&ft_mutex);
	return rc;
}