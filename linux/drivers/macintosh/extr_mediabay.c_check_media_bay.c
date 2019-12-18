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
struct media_bay_info {int content_id; scalar_t__ state; } ;
struct macio_dev {int dummy; } ;

/* Variables and functions */
 int MB_FD ; 
 int MB_FD1 ; 
 int MB_NO ; 
 struct media_bay_info* macio_get_drvdata (struct macio_dev*) ; 
 scalar_t__ mb_up ; 

int check_media_bay(struct macio_dev *baydev)
{
	struct media_bay_info* bay;
	int id;

	if (baydev == NULL)
		return MB_NO;

	/* This returns an instant snapshot, not locking, sine
	 * we may be called with the bay lock held. The resulting
	 * fuzzyness of the result if called at the wrong time is
	 * not actually a huge deal
	 */
	bay = macio_get_drvdata(baydev);
	if (bay == NULL)
		return MB_NO;
	id = bay->content_id;
	if (bay->state != mb_up)
		return MB_NO;
	if (id == MB_FD1)
		return MB_FD;
	return id;
}