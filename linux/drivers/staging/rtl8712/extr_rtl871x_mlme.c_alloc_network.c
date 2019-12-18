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
struct wlan_network {int dummy; } ;
struct mlme_priv {int dummy; } ;

/* Variables and functions */
 struct wlan_network* _r8712_alloc_network (struct mlme_priv*) ; 

__attribute__((used)) static struct	wlan_network *alloc_network(struct mlme_priv *pmlmepriv)
{
	return _r8712_alloc_network(pmlmepriv);
}