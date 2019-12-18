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
struct sta_priv {int /*<<< orphan*/  pallocated_stainfo_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfree_all_stainfo (struct sta_priv*) ; 

void _r8712_free_sta_priv(struct sta_priv *pstapriv)
{
	if (pstapriv) {
		/* be done before free sta_hash_lock */
		mfree_all_stainfo(pstapriv);
		kfree(pstapriv->pallocated_stainfo_buf);
	}
}