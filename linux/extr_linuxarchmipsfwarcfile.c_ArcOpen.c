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
typedef  enum linux_omode { ____Placeholder_linux_omode } linux_omode ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_CALL3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open ; 

LONG
ArcOpen(CHAR *Path, enum linux_omode OpenMode, ULONG *FileID)
{
	return ARC_CALL3(open, Path, OpenMode, FileID);
}