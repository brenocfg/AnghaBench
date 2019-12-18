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
struct SiS_Private {int SiS_IF_DEF_CH70xx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_SetCH700x (struct SiS_Private*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  SiS_SetCH701x (struct SiS_Private*,unsigned short,unsigned char) ; 

__attribute__((used)) static
void
SiS_SetCH70xx(struct SiS_Private *SiS_Pr, unsigned short reg, unsigned char val)
{
  if(SiS_Pr->SiS_IF_DEF_CH70xx == 1)
     SiS_SetCH700x(SiS_Pr, reg, val);
  else
     SiS_SetCH701x(SiS_Pr, reg, val);
}