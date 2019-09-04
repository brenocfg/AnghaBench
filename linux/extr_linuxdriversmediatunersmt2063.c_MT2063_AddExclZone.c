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
typedef  int u32 ;
struct MT2063_ExclZone_t {int max_; int min_; struct MT2063_ExclZone_t* next_; } ;
struct MT2063_AvoidSpursData_t {int f_if1_Center; int f_if1_bw; struct MT2063_ExclZone_t* usedZones; } ;

/* Variables and functions */
 struct MT2063_ExclZone_t* InsertNode (struct MT2063_AvoidSpursData_t*,struct MT2063_ExclZone_t*) ; 
 struct MT2063_ExclZone_t* RemoveNode (struct MT2063_AvoidSpursData_t*,struct MT2063_ExclZone_t*,struct MT2063_ExclZone_t*) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 

__attribute__((used)) static void MT2063_AddExclZone(struct MT2063_AvoidSpursData_t *pAS_Info,
			       u32 f_min, u32 f_max)
{
	struct MT2063_ExclZone_t *pNode = pAS_Info->usedZones;
	struct MT2063_ExclZone_t *pPrev = NULL;
	struct MT2063_ExclZone_t *pNext = NULL;

	dprintk(2, "\n");

	/*  Check to see if this overlaps the 1st IF filter  */
	if ((f_max > (pAS_Info->f_if1_Center - (pAS_Info->f_if1_bw / 2)))
	    && (f_min < (pAS_Info->f_if1_Center + (pAS_Info->f_if1_bw / 2)))
	    && (f_min < f_max)) {
		/*
		 *                1        2         3      4       5        6
		 *
		 *   New entry:  |---|    |--|      |--|    |-|    |---|    |--|
		 *                or       or        or     or      or
		 *   Existing:  |--|      |--|      |--|    |---|  |-|      |--|
		 */

		/*  Check for our place in the list  */
		while ((pNode != NULL) && (pNode->max_ < f_min)) {
			pPrev = pNode;
			pNode = pNode->next_;
		}

		if ((pNode != NULL) && (pNode->min_ < f_max)) {
			/*  Combine me with pNode  */
			if (f_min < pNode->min_)
				pNode->min_ = f_min;
			if (f_max > pNode->max_)
				pNode->max_ = f_max;
		} else {
			pNode = InsertNode(pAS_Info, pPrev);
			pNode->min_ = f_min;
			pNode->max_ = f_max;
		}

		/*  Look for merging possibilities  */
		pNext = pNode->next_;
		while ((pNext != NULL) && (pNext->min_ < pNode->max_)) {
			if (pNext->max_ > pNode->max_)
				pNode->max_ = pNext->max_;
			/*  Remove pNext, return ptr to pNext->next  */
			pNext = RemoveNode(pAS_Info, pNode, pNext);
		}
	}
}