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
struct net_device {int dummy; } ;

/* Variables and functions */
 int IFI_CANFD_FILTER_IDENT_CANFD ; 
 int IFI_CANFD_FILTER_IDENT_IDE ; 
 int IFI_CANFD_FILTER_IDENT_VALID ; 
 int IFI_CANFD_FILTER_MASK_EDL ; 
 int IFI_CANFD_FILTER_MASK_EXT ; 
 int IFI_CANFD_FILTER_MASK_VALID ; 
 int /*<<< orphan*/  ifi_canfd_set_filter (struct net_device*,int,int,int) ; 

__attribute__((used)) static void ifi_canfd_set_filters(struct net_device *ndev)
{
	/* Receive all CAN frames (standard ID) */
	ifi_canfd_set_filter(ndev, 0,
			     IFI_CANFD_FILTER_MASK_VALID |
			     IFI_CANFD_FILTER_MASK_EXT,
			     IFI_CANFD_FILTER_IDENT_VALID);

	/* Receive all CAN frames (extended ID) */
	ifi_canfd_set_filter(ndev, 1,
			     IFI_CANFD_FILTER_MASK_VALID |
			     IFI_CANFD_FILTER_MASK_EXT,
			     IFI_CANFD_FILTER_IDENT_VALID |
			     IFI_CANFD_FILTER_IDENT_IDE);

	/* Receive all CANFD frames */
	ifi_canfd_set_filter(ndev, 2,
			     IFI_CANFD_FILTER_MASK_VALID |
			     IFI_CANFD_FILTER_MASK_EDL |
			     IFI_CANFD_FILTER_MASK_EXT,
			     IFI_CANFD_FILTER_IDENT_VALID |
			     IFI_CANFD_FILTER_IDENT_CANFD |
			     IFI_CANFD_FILTER_IDENT_IDE);
}