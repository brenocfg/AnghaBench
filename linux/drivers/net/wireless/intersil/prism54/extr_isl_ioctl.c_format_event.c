#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct obj_mlme {int code; int /*<<< orphan*/  address; } ;
struct TYPE_3__ {scalar_t__ iw_mode; } ;
typedef  TYPE_1__ islpci_private ;

/* Variables and functions */
 int IW_CUSTOM_MAX ; 
 scalar_t__ IW_MODE_MASTER ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int snprintf (char*,int,char*,char const*,char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
format_event(islpci_private *priv, char *dest, const char *str,
	     const struct obj_mlme *mlme, u16 *length, int error)
{
	int n = snprintf(dest, IW_CUSTOM_MAX,
			 "%s %s %pM %s (%2.2X)",
			 str,
			 ((priv->iw_mode == IW_MODE_MASTER) ? "from" : "to"),
			 mlme->address,
			 (error ? (mlme->code ? " : REJECTED " : " : ACCEPTED ")
			  : ""), mlme->code);
	WARN_ON(n >= IW_CUSTOM_MAX);
	*length = n;
}