#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mib_sem; int /*<<< orphan*/ ** mib; } ;
typedef  TYPE_1__ islpci_private ;
struct TYPE_6__ {int flags; int size; int range; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OID_FLAG_CACHED ; 
 int OID_NUM_LAST ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 TYPE_4__* isl_oid ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prism54_mib_init (TYPE_1__*) ; 

int
mgt_init(islpci_private *priv)
{
	int i;

	priv->mib = kcalloc(OID_NUM_LAST, sizeof (void *), GFP_KERNEL);
	if (!priv->mib)
		return -ENOMEM;

	/* Alloc the cache */
	for (i = 0; i < OID_NUM_LAST; i++) {
		if (isl_oid[i].flags & OID_FLAG_CACHED) {
			priv->mib[i] = kcalloc(isl_oid[i].size,
					       (isl_oid[i].range + 1),
					       GFP_KERNEL);
			if (!priv->mib[i])
				return -ENOMEM;
		} else
			priv->mib[i] = NULL;
	}

	init_rwsem(&priv->mib_sem);
	prism54_mib_init(priv);

	return 0;
}