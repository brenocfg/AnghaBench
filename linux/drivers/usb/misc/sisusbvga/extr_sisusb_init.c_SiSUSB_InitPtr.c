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
struct SiS_Private {int /*<<< orphan*/  SiS_VCLKData; int /*<<< orphan*/  SiS_CRT1Table; int /*<<< orphan*/  SiS_RefIndex; int /*<<< orphan*/  SiS_EModeIDTable; int /*<<< orphan*/  SiS_SModeIDTable; int /*<<< orphan*/  SiS_StandTable; int /*<<< orphan*/  SiS_ModeResInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiSUSB_CRT1Table ; 
 int /*<<< orphan*/  SiSUSB_EModeIDTable ; 
 int /*<<< orphan*/  SiSUSB_ModeResInfo ; 
 int /*<<< orphan*/  SiSUSB_RefIndex ; 
 int /*<<< orphan*/  SiSUSB_SModeIDTable ; 
 int /*<<< orphan*/  SiSUSB_StandTable ; 
 int /*<<< orphan*/  SiSUSB_VCLKData ; 

__attribute__((used)) static void SiSUSB_InitPtr(struct SiS_Private *SiS_Pr)
{
	SiS_Pr->SiS_ModeResInfo = SiSUSB_ModeResInfo;
	SiS_Pr->SiS_StandTable = SiSUSB_StandTable;

	SiS_Pr->SiS_SModeIDTable = SiSUSB_SModeIDTable;
	SiS_Pr->SiS_EModeIDTable = SiSUSB_EModeIDTable;
	SiS_Pr->SiS_RefIndex = SiSUSB_RefIndex;
	SiS_Pr->SiS_CRT1Table = SiSUSB_CRT1Table;

	SiS_Pr->SiS_VCLKData = SiSUSB_VCLKData;
}