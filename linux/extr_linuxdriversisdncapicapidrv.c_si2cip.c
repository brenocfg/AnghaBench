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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */

__attribute__((used)) static inline u16 si2cip(u8 si1, u8 si2)
{
	static const u8 cip[17][5] =
		{
			/*  0  1  2  3  4  */
			{0, 0, 0, 0, 0},	/*0 */
			{16, 16, 4, 26, 16},	/*1 */
			{17, 17, 17, 4, 4},	/*2 */
			{2, 2, 2, 2, 2},	/*3 */
			{18, 18, 18, 18, 18},	/*4 */
			{2, 2, 2, 2, 2},	/*5 */
			{0, 0, 0, 0, 0},	/*6 */
			{2, 2, 2, 2, 2},	/*7 */
			{2, 2, 2, 2, 2},	/*8 */
			{21, 21, 21, 21, 21},	/*9 */
			{19, 19, 19, 19, 19},	/*10 */
			{0, 0, 0, 0, 0},	/*11 */
			{0, 0, 0, 0, 0},	/*12 */
			{0, 0, 0, 0, 0},	/*13 */
			{0, 0, 0, 0, 0},	/*14 */
			{22, 22, 22, 22, 22},	/*15 */
			{27, 27, 27, 28, 27}	/*16 */
		};
	if (si1 > 16)
		si1 = 0;
	if (si2 > 4)
		si2 = 0;

	return (u16) cip[si1][si2];
}