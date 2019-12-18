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
typedef  int const u32 ;
typedef  enum dvbs2_mod_cod { ____Placeholder_dvbs2_mod_cod } dvbs2_mod_cod ;
typedef  enum dvbs2_fectype { ____Placeholder_dvbs2_fectype } dvbs2_fectype ;

/* Variables and functions */
 int DVBS2_16K ; 
 int DVBS2_32APSK_9_10 ; 
 int DVBS2_QPSK_1_4 ; 

__attribute__((used)) static u32 dvbs2_nbch(enum dvbs2_mod_cod mod_cod, enum dvbs2_fectype fectype)
{
	static const u32 nbch[][2] = {
		{    0,     0}, /* DUMMY_PLF   */
		{16200,  3240}, /* QPSK_1_4,   */
		{21600,  5400}, /* QPSK_1_3,   */
		{25920,  6480}, /* QPSK_2_5,   */
		{32400,  7200}, /* QPSK_1_2,   */
		{38880,  9720}, /* QPSK_3_5,   */
		{43200, 10800}, /* QPSK_2_3,   */
		{48600, 11880}, /* QPSK_3_4,   */
		{51840, 12600}, /* QPSK_4_5,   */
		{54000, 13320}, /* QPSK_5_6,   */
		{57600, 14400}, /* QPSK_8_9,   */
		{58320, 16000}, /* QPSK_9_10,  */
		{43200,  9720}, /* 8PSK_3_5,   */
		{48600, 10800}, /* 8PSK_2_3,   */
		{51840, 11880}, /* 8PSK_3_4,   */
		{54000, 13320}, /* 8PSK_5_6,   */
		{57600, 14400}, /* 8PSK_8_9,   */
		{58320, 16000}, /* 8PSK_9_10,  */
		{43200, 10800}, /* 16APSK_2_3, */
		{48600, 11880}, /* 16APSK_3_4, */
		{51840, 12600}, /* 16APSK_4_5, */
		{54000, 13320}, /* 16APSK_5_6, */
		{57600, 14400}, /* 16APSK_8_9, */
		{58320, 16000}, /* 16APSK_9_10 */
		{48600, 11880}, /* 32APSK_3_4, */
		{51840, 12600}, /* 32APSK_4_5, */
		{54000, 13320}, /* 32APSK_5_6, */
		{57600, 14400}, /* 32APSK_8_9, */
		{58320, 16000}, /* 32APSK_9_10 */
	};

	if (mod_cod >= DVBS2_QPSK_1_4 &&
	    mod_cod <= DVBS2_32APSK_9_10 && fectype <= DVBS2_16K)
		return nbch[mod_cod][fectype];
	return 64800;
}