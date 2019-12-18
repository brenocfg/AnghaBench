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
struct hl_fpriv {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpriv_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void hl_hpriv_put(struct hl_fpriv *hpriv)
{
	kref_put(&hpriv->refcount, hpriv_release);
}